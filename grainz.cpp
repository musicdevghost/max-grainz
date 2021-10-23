#include "grainz.h"

namespace grainz {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Change __m_change_14;
	Data m_envhanning_2;
	Data m_envad_7;
	Data m_samplebuffertwo_10;
	Data m_samplebufferone_8;
	Delta __m_delta_13;
	Phasor __m_phasor_12;
	int __exception;
	int vectorsize;
	t_sample samples_to_seconds;
	t_sample __m_count_15;
	t_sample __m_carry_17;
	t_sample __m_latch_20;
	t_sample m_gate1_rec_11;
	t_sample m_ctrl2_size_9;
	t_sample m_ctrl3_spray_6;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample __m_count_21;
	t_sample m_ctrl1_position_3;
	t_sample m_ctrl4_density_5;
	t_sample m_gain_4;
	t_sample __m_carry_23;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_envhanning_2.reset("envhanning", ((int)4096), ((int)1));
		m_ctrl1_position_3 = ((int)0);
		m_gain_4 = ((t_sample)0.1);
		m_ctrl4_density_5 = ((int)0);
		m_ctrl3_spray_6 = ((int)0);
		m_envad_7.reset("envad", ((int)4096), ((int)1));
		m_samplebufferone_8.reset("samplebufferone", ((int)132300), ((int)2));
		m_ctrl2_size_9 = ((int)0);
		m_samplebuffertwo_10.reset("samplebuffertwo", ((int)132300), ((int)2));
		m_gate1_rec_11 = ((int)0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_12.reset(0);
		__m_delta_13.reset(0);
		__m_change_14.reset(0);
		__m_count_15 = 0;
		__m_carry_17 = 0;
		__m_latch_20 = 0;
		__m_count_21 = 0;
		__m_carry_23 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		samples_to_seconds = (1 / samplerate);
		int gt_4927 = (m_gate1_rec_11 > ((t_sample)0.5));
		int samplebufferone_dim = m_samplebufferone_8.dim;
		int samplebufferone_channels = m_samplebufferone_8.channels;
		int dim_4989 = samplebufferone_dim;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out2 = ((int)0);
			t_sample out1 = ((int)0);
			t_sample out4 = in1;
			t_sample out3 = in1;
			t_sample sub_8690 = (m_ctrl4_density_5 - ((int)0));
			t_sample scale_8687 = ((safepow((sub_8690 * ((t_sample)1)), ((int)1)) * ((int)15)) + ((int)0));
			t_sample scale_4974 = scale_8687;
			if ((((int)0) != 0)) {
				__m_phasor_12.phase = 0;
				
			};
			t_sample phasor_4977 = __m_phasor_12(scale_4974, samples_to_seconds);
			t_sample delta_4976 = __m_delta_13(phasor_4977);
			int lt_4975 = (delta_4976 < ((int)0));
			int gen_4978 = lt_4975;
			int int_4956 = int(gen_4978);
			int change_4957 = __m_change_14(int_4956);
			int eqp_4958 = ((int_4956 == change_4957) ? int_4956 : 0);
			int gen_4959 = eqp_4958;
			t_sample out5 = gen_4959;
			int trigger_4952 = gen_4959;
			int trigger_4922 = trigger_4952;
			int switch_4928 = (gt_4927 ? ((int)0) : ((int)1));
			__m_count_15 = (((int)0) ? 0 : (fixdenorm(__m_count_15 + ((int)1))));
			int carry_16 = 0;
			if ((((int)0) != 0)) {
				__m_count_15 = 0;
				__m_carry_17 = 0;
				
			} else if (((dim_4989 > 0) && (__m_count_15 >= dim_4989))) {
				int wraps_18 = (__m_count_15 / dim_4989);
				__m_carry_17 = (__m_carry_17 + wraps_18);
				__m_count_15 = (__m_count_15 - (wraps_18 * dim_4989));
				carry_16 = 1;
				
			};
			int counter_4997 = __m_count_15;
			int counter_4998 = carry_16;
			int counter_4999 = __m_carry_17;
			int mul_4924 = (counter_4997 * switch_4928);
			bool index_ignore_19 = ((mul_4924 >= samplebufferone_dim) || (mul_4924 < 0));
			if ((!index_ignore_19)) {
				m_samplebufferone_8.write(in1, mul_4924, 0);
				
			};
			t_sample sub_8694 = (m_ctrl2_size_9 - ((int)0));
			t_sample scale_8691 = ((safepow((sub_8694 * ((t_sample)1)), ((int)1)) * ((int)1000)) + ((int)0));
			t_sample scale_4961 = scale_8691;
			t_sample mstosamps_4960 = (scale_4961 * (samplerate * 0.001));
			__m_latch_20 = ((trigger_4952 != 0) ? mstosamps_4960 : __m_latch_20);
			t_sample latch_4953 = __m_latch_20;
			t_sample size_4962 = latch_4953;
			t_sample size_4981 = size_4962;
			__m_count_21 = (trigger_4922 ? 0 : (fixdenorm(__m_count_21 + m_history_1)));
			int carry_22 = 0;
			if ((trigger_4922 != 0)) {
				__m_count_21 = 0;
				__m_carry_23 = 0;
				
			} else if (((size_4981 > 0) && (__m_count_21 >= size_4981))) {
				int wraps_24 = (__m_count_21 / size_4981);
				__m_carry_23 = (__m_carry_23 + wraps_24);
				__m_count_21 = (__m_count_21 - (wraps_24 * size_4981));
				carry_22 = 1;
				
			};
			t_sample counter_4990 = __m_count_21;
			int counter_4991 = carry_22;
			int counter_4992 = __m_carry_23;
			t_sample sub_4968 = (size_4981 - ((int)1));
			int lt_4969 = (counter_4990 < sub_4968);
			t_sample history_4967_next_8678 = fixdenorm(lt_4969);
			m_history_1 = history_4967_next_8678;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_envhanning(void * _value) {
		m_envhanning_2.setbuffer(_value);
	};
	inline void set_ctrl1_position(t_param _value) {
		m_ctrl1_position_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_gain(t_param _value) {
		m_gain_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl4_density(t_param _value) {
		m_ctrl4_density_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl3_spray(t_param _value) {
		m_ctrl3_spray_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_envad(void * _value) {
		m_envad_7.setbuffer(_value);
	};
	inline void set_samplebufferone(void * _value) {
		m_samplebufferone_8.setbuffer(_value);
	};
	inline void set_ctrl2_size(t_param _value) {
		m_ctrl2_size_9 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_samplebuffertwo(void * _value) {
		m_samplebuffertwo_10.setbuffer(_value);
	};
	inline void set_gate1_rec(t_param _value) {
		m_gate1_rec_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 5;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 10; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4", "gate1" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_ctrl1_position(value); break;
		case 1: self->set_ctrl2_size(value); break;
		case 2: self->set_ctrl3_spray(value); break;
		case 3: self->set_ctrl4_density(value); break;
		case 4: self->set_envad(ref); break;
		case 5: self->set_envhanning(ref); break;
		case 6: self->set_gain(value); break;
		case 7: self->set_gate1_rec(value); break;
		case 8: self->set_samplebufferone(ref); break;
		case 9: self->set_samplebuffertwo(ref); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_ctrl1_position_3; break;
		case 1: *value = self->m_ctrl2_size_9; break;
		case 2: *value = self->m_ctrl3_spray_6; break;
		case 3: *value = self->m_ctrl4_density_5; break;
		
		
		case 6: *value = self->m_gain_4; break;
		case 7: *value = self->m_gate1_rec_11; break;
		
		
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(10 * sizeof(ParamInfo));
	self->__commonstate.numparams = 10;
	// initialize parameter 0 ("m_ctrl1_position_3")
	pi = self->__commonstate.params + 0;
	pi->name = "ctrl1_position";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl1_position_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl2_size_9")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl2_size";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl2_size_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ctrl3_spray_6")
	pi = self->__commonstate.params + 2;
	pi->name = "ctrl3_spray";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl3_spray_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ctrl4_density_5")
	pi = self->__commonstate.params + 3;
	pi->name = "ctrl4_density";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl4_density_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_envad_7")
	pi = self->__commonstate.params + 4;
	pi->name = "envad";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_envhanning_2")
	pi = self->__commonstate.params + 5;
	pi->name = "envhanning";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_gain_4")
	pi = self->__commonstate.params + 6;
	pi->name = "gain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gain_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_gate1_rec_11")
	pi = self->__commonstate.params + 7;
	pi->name = "gate1_rec";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate1_rec_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_samplebufferone_8")
	pi = self->__commonstate.params + 8;
	pi->name = "samplebufferone";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_samplebuffertwo_10")
	pi = self->__commonstate.params + 9;
	pi->name = "samplebuffertwo";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // grainz::
