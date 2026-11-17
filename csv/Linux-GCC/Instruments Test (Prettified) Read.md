
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19899.9 | 0.0257552 | 894.947ms | 183677 | 40 | 205.589 | 8802.48 | 0.482963 | 0.124011 | 1(Win) | true |
| simdjson (stage-1) | 16283.2 | 0.143794 | 1084.2ms | 183677 | 4890 | 1.17009e+06 | 10757.6 | 0.00216551 | 0.15167 | 2(Loss) | true |
