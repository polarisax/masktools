#ifndef __Mt_Expand_H__
#define __Mt_Expand_H__

#include "../morphologic.h"

namespace Filtering { namespace MaskTools { namespace Filters { namespace Morphologic { namespace Expand {


extern Processor *expand_square_c;
extern Processor *expand_square_sse2;
extern Processor *expand_square_asse2;

extern Processor *expand_horizontal_c;
extern Processor *expand_horizontal_sse2;
extern Processor *expand_horizontal_asse2;

extern Processor *expand_vertical_c;
extern Processor *expand_vertical_sse2;
extern Processor *expand_vertical_asse2;

extern Processor *expand_both_c;
extern Processor *expand_both_sse2;
extern Processor *expand_both_asse2;

extern Processor *expand_custom_c;

class Expand : public Morphologic::MorphologicFilter
{
public:
   Expand(const Parameters&parameters) : Morphologic::MorphologicFilter( parameters )
   {
      /* add the processors */
      if ( parameters["mode"].toString() == "square" )
      {
         processors.push_back(Filtering::Processor<Processor>(expand_square_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         processors.push_back(Filtering::Processor<Processor>(expand_square_sse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_NONE, 16), 1));
         processors.push_back(Filtering::Processor<Processor>(expand_square_asse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_16, 16), 2));
      }
      else if ( parameters["mode"].toString() == "horizontal" )
      {
         processors.push_back(Filtering::Processor<Processor>(expand_horizontal_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         processors.push_back(Filtering::Processor<Processor>(expand_horizontal_sse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_NONE, 16), 1));
         processors.push_back(Filtering::Processor<Processor>(expand_horizontal_asse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_16, 16), 2));
      }
      else if ( parameters["mode"].toString() == "vertical" )
      {
         processors.push_back(Filtering::Processor<Processor>(expand_vertical_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         processors.push_back(Filtering::Processor<Processor>(expand_vertical_sse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_NONE, 16), 1));
         processors.push_back(Filtering::Processor<Processor>(expand_vertical_asse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_16, 16), 2));
      }
      else if ( parameters["mode"].toString() == "both" )
      {
         processors.push_back(Filtering::Processor<Processor>(expand_both_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         processors.push_back(Filtering::Processor<Processor>(expand_both_sse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_NONE, 16), 1));
         processors.push_back(Filtering::Processor<Processor>(expand_both_asse2, Constraint(CPU_SSE2, MODULO_NONE, MODULO_NONE, ALIGNMENT_16, 16), 2));
      }
      else
      {
         processors.push_back(Filtering::Processor<Processor>(expand_custom_c, Constraint(CPU_NONE, 1, 1, 1, 1), 0));
         FillCoordinates( parameters["mode"].toString() );
      }
   }

   static Signature Expand::filter_signature()
   {
      Signature signature = "mt_expand";

      signature.add( Parameter(TYPE_CLIP, "") );
      signature.add( Parameter(255, "thY") );
      signature.add( Parameter(255, "thC") );
      signature.add( Parameter(String("square"), "mode") );

      return add_defaults( signature );
   }
};

} } } } } // namespace Expand, Morphologic, Filter, MaskTools, Filtering

#endif