
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1837.85 | 0.152503 | 785.914ms | 1313 | 4890 | 5279.27 | 681.326 | 0.016974 | 2.96287 | 13.4813 | 2.46459 | 0.000764262 | 0.000138305 | 3.31746e-05 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 918.258 | 0.0540311 | 849.543ms | 1313 | 4890 | 2654.58 | 1363.64 | 0.230546 | 5.77837 | 27.5171 | 6.70373 | 0.00139941 | 0.000128026 | 3.25516e-05 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 916.113 | 0.107553 | 851.965ms | 1313 | 30 | 64.8333 | 1366.83 | 0.226288 | 5.89185 | 24.4021 | 2.97563 | 0.000761615 | 0.000101549 | 0 | 2(Tie) | true |
| simdjson (ondemand) | 399.761 | 0.111286 | 1027.26ms | 1313 | 640 | 7776.54 | 3132.31 | 0.0327841 | 13.0451 | 55.243 | 10.933 | 0.00130308 | 0.000105912 | 2.38005e-06 | 4(Loss) | true |
