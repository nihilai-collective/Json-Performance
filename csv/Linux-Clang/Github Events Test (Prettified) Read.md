
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17074.1 | 0.0383484 | 1080.77ms | 65103 | 80 | 155.564 | 3636.32 | 0.028867 | 0.304984 | 1.6557 | 0.0748967 | 3.12966e-05 | 2.30404e-06 | 1.92003e-07 | 1(Win) | true |
| simdjson (stage-1) | 16094.2 | 0.0341263 | 1101.08ms | 65103 | 30 | 51.9954 | 3857.73 | 0.0129627 | 0.324119 | 1.50202 | 0.0630693 | 5.7345e-05 | 2.56005e-06 | 0 | 2(Loss) | true |
