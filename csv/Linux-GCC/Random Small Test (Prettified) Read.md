
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2060.4 | 0.0530148 | 1101.44ms | 8150 | 640 | 2559.7 | 3772.3 | 0.00890457 | 2.52714 | 10.5704 | 1.9346 | 0.00264225 | 7.59202e-05 | 4.90798e-05 | 1(Win) | true |
| simdjson (ondemand) | 1720.65 | 0.0655547 | 1174.04ms | 8150 | 1280 | 11224 | 4517.15 | 0.033339 | 3.01574 | 11.7036 | 2.09755 | 0.00243184 | 5.19555e-05 | 2.55943e-05 | 2(Loss) | true |
