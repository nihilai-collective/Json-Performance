
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2512.72 | 0.0947698 | 1074.11ms | 8150 | 640 | 5499.82 | 3093.25 | 0.116873 | 2.07714 | 9.01092 | 1.58822 | 0.0023217 | 2.28144e-05 | 8.81902e-06 | 1(Win) | true |
| simdjson (ondemand) | 1989.93 | 0.032446 | 1145.47ms | 8150 | 4890 | 7853.65 | 3905.9 | 0.169859 | 2.60926 | 10.1675 | 1.75914 | 0.00273717 | 2.73753e-05 | 1.43024e-06 | 2(Loss) | true |
