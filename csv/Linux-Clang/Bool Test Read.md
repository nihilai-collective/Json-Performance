
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1181.47 | 0.153988 | 778.603ms | 905 | 320 | 404.928 | 730.513 | 0.00171116 | 4.60225 | 22.9392 | 2.29503 | 0.00450276 | 0.000131215 | 2.41713e-05 | 1(Win) | true |
| simdjson (stage-1) | 449.47 | 0.127228 | 906.692ms | 905 | 1280 | 7639.65 | 1920.21 | 0.0997795 | 11.6798 | 61.2597 | 4.91381 | 0.00221081 | 0.000108771 | 1.55387e-05 | 2(Loss) | true |
