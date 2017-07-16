# Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS

---

Description of problem 

---

Our goal is to deal with narrowband digital communications using linear modulation in the presence of multipath.

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Multipath-effect-block-diagram.PNG)

With symbol rate sampling at the receiver, the received signal may be expressed as

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Sample-at-the-receiver.PNG)

where d[n] is the sequence of transmitted symbols.

A QPSK alphabet is assumed so that

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/Transmitted-signal.PNG)

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

Least Mean Square ( LMS ) filter for adaptive equalization

---

Least mean squares (LMS) algorithms are a class of adaptive filter used to mimic a desired filter by finding the filter 

coefficients that relate to producing the least mean square of the error signal (difference between the desired and the actual 

signal).

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/LMS-algorithm.PNG)

---

Outcome of LMS adaptive equalization

---

![alt text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/LMS%20filter%20equlization%20for%20QPSK.png)

---

Recursive Least Square ( RLS ) filter for adaptive equalization

---

The Recursive least squares (RLS) is an adaptive filter which recursively finds the coefficients that minimize a weighted linear least squares cost function relating to the input signals. This is in contrast to other algorithms such as the least mean squares (LMS) that aim to reduce the mean square error. In the derivation of the RLS, the input signals are considered deterministic, while for the LMS and similar algorithm they are considered stochastic. Compared to most of its competitors, the RLS exhibits extremely fast convergence. However, this benefit comes at the cost of high computational complexity.

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/RLS-algorithm.PNG)


---

Outcome of RLS adaptive equalization

---

![alt_text](https://github.com/wei-lin-liao/Communication-System-and-Signal-Processing/blob/master/Adpative-Equalizer-for-Digital-Communication-LMS-and-RLS/images/RLS%20filter%20equlization%20for%20QPSK.png)



