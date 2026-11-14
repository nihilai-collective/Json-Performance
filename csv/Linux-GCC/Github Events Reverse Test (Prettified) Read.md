
----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1065.42 | 0.0473845 | 6560.58ms | 65103 | 640 | 487989 | 58274.6 | 0.0156343 | 4.83333 | 16.9534 | 3.39068 | 0.0149041 | 6.30011e-05 | 4.44008e-05 | 1(Win) | true |
| simdjson (ondemand) | 606.105 | 0.11296 | 5607.37ms | 65103 | 320 | 4.28457e+06 | 102436 | 0.0934647 | 8.47037 | 30.2332 | 6.06999 | 0.0537049 | 4.14247e-05 | 1.89123e-05 | 2(Loss) | true |
