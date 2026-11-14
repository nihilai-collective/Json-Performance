
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 406.315 | 0.0812067 | 6855.94ms | 1834197 | 80 | 9.77781e+08 | 4.3051e+06 | 0.0741428 | 12.4138 | 57.4684 | 12.6515 | 0.0380977 | 0.323196 | 0.00130415 | 1(Win) | true |
| simdjson (ondemand) | 280.734 | 0.11341 | 9707.44ms | 1834197 | 30 | 1.49804e+09 | 6.23091e+06 | 0.0646443 | 18.1388 | 98.9655 | 20.481 | 0.0491731 | 0.767355 | 0.0139982 | 2(Loss) | true |
