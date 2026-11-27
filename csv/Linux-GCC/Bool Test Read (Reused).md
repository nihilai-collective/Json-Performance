
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 910.705 | 0.107579 | 99.7327ms | 905 | 30 | 31.1828 | 947.7 | 0.0281462 | 2.64678 | 1(Win) | true |
| simdjson (ondemand) | 548.797 | 0.174826 | 159.159ms | 905 | 30 | 226.782 | 1572.67 | 0.188996 | 4.43378 | 2(Loss) | true |
