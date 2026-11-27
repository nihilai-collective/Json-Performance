
----
### Google Maps Response Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1655.23 | 0.0419016 | 2220.79ms | 25388 | 4890 | 183701 | 14627.5 | 0.0132644 | 3.0751 | 14.2762 | 2.78202 | 0.00658798 | 3.34522e-05 | 1.87197e-05 | 1(Win) | true |
| simdjson (ondemand) | 1498.49 | 0.0452903 | 2361.37ms | 25388 | 2560 | 137088 | 16157.5 | 0.0437298 | 3.39843 | 15.1852 | 2.8545 | 0.00737476 | 3.97733e-05 | 2.44333e-05 | 2(Loss) | true |
