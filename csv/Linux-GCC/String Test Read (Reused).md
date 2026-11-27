
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 873.242 | 0.0463319 | 510.944ms | 4215 | 30 | 136.461 | 4603.23 | 0.0572389 | 2.81915 | 1(Win) | true |
| simdjson (ondemand) | 862.57 | 0.0717668 | 505.633ms | 4215 | 80 | 894.838 | 4660.19 | 0.0845638 | 2.85457 | 2(Loss) | true |
