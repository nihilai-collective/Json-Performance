
----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 928.669 | 0.0269679 | 6215.4ms | 53331 | 2560 | 558435 | 54767 | 0.125497 | 5.54239 | 19.7759 | 3.94037 | 0.016977 | 5.17186e-05 | 1.98934e-05 | 1(Win) | true |
| simdjson (ondemand) | 485.426 | 0.0592256 | 5750.34ms | 53331 | 1280 | 4.92882e+06 | 104775 | 0.171655 | 10.5933 | 36.9768 | 7.48488 | 0.0717104 | 6.19217e-05 | 1.79598e-05 | 2(Loss) | true |
