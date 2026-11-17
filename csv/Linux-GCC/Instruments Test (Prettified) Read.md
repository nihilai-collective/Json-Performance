
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2495.88 | 0.054981 | 7768.34ms | 183677 | 640 | 952940 | 70182.7 | 0.0626592 | 2.04012 | 8.82198 | 1.69505 | 0.00211552 | 1.16968e-05 | 8.23456e-06 | 1(Win) | true |
| simdjson (ondemand) | 2397.48 | 0.051642 | 8021.48ms | 183677 | 4890 | 6.96171e+06 | 73063.5 | 0.0286974 | 2.12637 | 9.5929 | 1.50224 | 0.00353024 | 3.32784e-05 | 2.4416e-05 | 2(Loss) | true |
