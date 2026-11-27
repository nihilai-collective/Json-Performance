
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.09 | 0.0589188 | 1051.61ms | 4926 | 640 | 2394.11 | 3282.68 | 0.00157072 | 3.64371 | 15.5514 | 3.01198 | 0.00367819 | 2.79131e-05 | 5.7095e-06 | 1(Win) | true |
| simdjson (ondemand) | 1073.7 | 0.0347299 | 1163.8ms | 4926 | 2560 | 5911.15 | 4375.35 | 0.0565795 | 4.83893 | 18.5051 | 3.43402 | 0.00473682 | 7.50165e-05 | 2.86268e-05 | 2(Loss) | true |
