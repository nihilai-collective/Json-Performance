
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1473.15 | 0.044044 | 88.9446ms | 1313 | 320 | 44.8495 | 849.997 | 0.0767795 | 1.62685 | 1(Win) | true |
| Glaze | 880.797 | 0.0362625 | 146.309ms | 1313 | 160 | 42.5219 | 1421.64 | 0.105624 | 2.75808 | 2(Loss) | true |
| simdjson (ondemand) | 327.725 | 0.0371928 | 380.296ms | 1313 | 160 | 323.109 | 3820.81 | 0.340745 | 7.50031 | 3(Loss) | true |
