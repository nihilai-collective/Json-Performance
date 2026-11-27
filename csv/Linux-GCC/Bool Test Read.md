
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1983.04 | 0.104872 | 46.5846ms | 905 | 320 | 66.6657 | 435.228 | 0.0567553 | 1.17337 | 1(Win) | true |
| simdjson (stage-1) | 956.396 | 0.0233338 | 93.9956ms | 905 | 320 | 14.1887 | 902.425 | 0.0954845 | 2.51605 | 2(Loss) | true |
