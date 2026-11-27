
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1959.14 | 0.0881659 | 46.1382ms | 905 | 320 | 48.2745 | 440.538 | 0.0695657 | 1.18998 | 1(Win) | true |
| simdjson (stage-1) | 803.16 | 0.168995 | 98.3068ms | 905 | 30 | 98.9379 | 1074.6 | 0.524562 | 3.00685 | 2(Loss) | true |
