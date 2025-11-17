# include <iostream>
# include "pugixml.hpp"
#include "market_data_normalization/parse_swap_from_xml.hpp"
#include "market_data_normalization/fpml_swap.hpp"

Swap parseSwapFromXML(const std::string& xmlContent){
    pugi::xml_document doc;
    if (!doc.load_string(xmlContent.c_str())){
        throw std::runtime_error("Failed to parse XML content");
        
    }
    
    Swap result;
    for (const auto& swapStream : doc.child("swap").children("swapStream")) {
            const auto payer = swapStream.child("payerPartyReference");
            const auto receiver = swapStream.child("receiverPartyReference");
            if (payer && receiver) {
                FixedLeg fixed;
                fixed.payer = payer.attribute("href").value();
                fixed.receiver = receiver.attribute("href").value();
                fixed.notional = std::stod(swapStream.child("notionalSchedule")
                                            .child("notionalStepSchedule")
                                            .child("initialValue").child_value());
                fixed.fixedRate = std::stod(swapStream.child("calculation")
                                                .child("fixedRateSchedule")
                                                .child("initialValue").child_value());
                result.fixedLeg = fixed;
            } else {
                FloatingLeg floating;
                auto floatCalc = swapStream.child("calculation").child("floatingRateCalculation");
                floating.index = floatCalc.child("floatingRateIndex").child_value();
                floating.tenorMonths = std::stoi(floatCalc.child("indexTenor")
                                                           .child("periodMultiplier").child_value());
                result.floatingLeg = floating;
            }
        }

        return result;
    
}
