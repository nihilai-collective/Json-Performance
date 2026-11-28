
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1811.57 | 0.163857 | 50.0584ms | 905 | 80 | 48.7538 | 476.425 | 0.319071 | 1.28808 | 1(Win) | true |
| Glaze | 1459.32 | 0.0300212 | 62.629ms | 905 | 320 | 10.0879 | 591.422 | 0.094492 | 1.61972 | 2(Loss) | true |
| simdjson (ondemand) | 436.264 | 0.0527278 | 201.252ms | 905 | 30 | 32.6437 | 1978.33 | 0.350913 | 5.59827 | 3(Loss) | true |
