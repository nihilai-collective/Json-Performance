
----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 903.9 | 0.0239239 | 9602.08ms | 83958 | 1280 | 574853 | 88581.3 | 0.225463 | 5.68802 | 24.715 | 5.23774 | 0.00820764 | 1.0701e-05 | 3.8989e-06 | 1(Win) | true |
| simdjson (ondemand) | 311.833 | 0.0538835 | 6740.38ms | 83958 | 640 | 1.22511e+07 | 256768 | 0.0909545 | 16.3983 | 89.3675 | 18.9301 | 0.0282328 | 4.45163e-05 | 2.12532e-05 | 2(Loss) | true |
