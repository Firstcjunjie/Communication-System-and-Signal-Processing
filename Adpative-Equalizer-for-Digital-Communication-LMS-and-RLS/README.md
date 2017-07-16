# Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS

---

Description of problem 

---

Our goal is to deal with narrowband digital communications using linear modulation in the presence of multipath.

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Multipath-effect-block-diagram.PNG)

With symbol rate sampling at the receiver, the received signal may be expressed as

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Sample-at-the-receiver.PNG)

where d[n] is the sequence of transmitted symbols.

q[n] is the symbol-rate sampled version of the multipath distorted pulse symbol waveform

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Symbol-rate-sampled-version-of-the-multipath-distorted-pulse-symbol-waveform.PNG)

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Waveform-description.PNG)

p(t) is assumed to have a raised cosine spectrum so that it may described in the time domain as

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Raised-cosine.PNG)

q[n] ( 2-ray ) may be expressed as 

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Distorted-waveform.PNG)

The process of equalization involves finding an inverse filter with impulse response w[n]

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Filter-block-diagram.PNG)

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Filter-taps-and-sequence-of-recerived-symbols.PNG)

---

Least Mean Square filter for adaptive equalization

---

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/LMS-algorithm.PNG)

---

Outcome of LMS adaptive equalization

---

![alt text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/LMS%20filter%20equlization%20for%20QPSK.png)

