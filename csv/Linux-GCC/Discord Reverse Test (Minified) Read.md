
----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 659.111 | 0.0566241 | 8170.2ms | 56369 | 4890 | 1.04298e+07 | 81560.9 | 0.329043 | 3.75499 | 1(Win) | true |
| simdjson (ondemand) | 175.665 | 0.117533 | 7922.51ms | 56369 | 160 | 2.06991e+07 | 306024 | 0.387466 | 14.0927 | 2(Loss) | true |
