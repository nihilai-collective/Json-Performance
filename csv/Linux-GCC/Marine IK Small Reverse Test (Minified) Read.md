
----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 316.327 | 0.0244105 | 2115.17ms | 4604 | 2560 | 29389.6 | 13880.3 | 0.0518341 | 16.3202 | 67.2322 | 14.6577 | 0.0241123 | 7.55966e-05 | 2.1296e-05 | 1(Win) | true |
| simdjson (ondemand) | 240.914 | 0.0871897 | 2545.09ms | 4604 | 160 | 40401.6 | 18225.3 | 0.0115897 | 21.4136 | 105.422 | 22.0865 | 0.023337 | 6.78758e-05 | 2.17202e-05 | 2(Loss) | true |
