
----
### Stream Formats Small Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3740.35 | 0.147045 | 6195.57ms | 16002592 | 40 | 1.43985e+09 | 4.08017e+06 | 0.0727303 | 1.3572 | 7.61693 | 1.22417 | 0.000786846 | 0.0325532 | 0.00609576 | 1(Win) | true |
| simdjson (ondemand) | 3189.39 | 0.0969197 | 7196.1ms | 16002592 | 30 | 6.45226e+08 | 4.78501e+06 | 0.180374 | 1.58358 | 8.48831 | 1.2264 | 0.00141822 | 0.0354204 | 0.00928246 | 2(Loss) | true |
