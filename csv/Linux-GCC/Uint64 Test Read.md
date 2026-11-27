
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2417.65 | 0.0264641 | 50.6075ms | 1213 | 2560 | 41.0478 | 478.484 | 0.0967531 | 0.968986 | 1(Win) | true |
| simdjson (stage-1) | 975.046 | 0.0519345 | 125.234ms | 1213 | 80 | 30.372 | 1186.41 | 0.0706408 | 2.48386 | 2(Loss) | true |
