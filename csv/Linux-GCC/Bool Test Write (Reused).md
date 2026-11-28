
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3267.99 | 0.341746 | 33.6532ms | 905 | 30 | 24.4379 | 264.1 | 0.113464 | 0.685488 | 1(Win) | true |
| simdjson (reflection) | 2536.59 | 0.0806601 | 41.1142ms | 905 | 40 | 3.01282 | 340.25 | 0.0244978 | 0.899917 | 2(Loss) | true |
| Glaze | 1122.44 | 0.151439 | 85.516ms | 905 | 80 | 108.475 | 768.925 | 0.0650682 | 2.12983 | 3(Loss) | true |
