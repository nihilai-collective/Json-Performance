
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 740.221 | 0.0357866 | 493.168ms | 3873 | 30 | 95.6609 | 4989.83 | 0.0467399 | 3.32524 | 1(Win) | true |
| simdjson (ondemand) | 520.962 | 0.060736 | 718.67ms | 3873 | 40 | 741.712 | 7089.93 | 0.45549 | 4.7336 | 2(Loss) | true |
