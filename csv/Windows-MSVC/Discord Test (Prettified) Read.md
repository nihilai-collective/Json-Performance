
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1631.84 | 0.456558 | 5090.34ms | 83958 | 320 | 1.60588e+07 | 49066.6 | 0.171617 | 1.51633 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1348.85 | 0.33947 | 6229ms | 83958 | 160 | 6.49712e+06 | 59360.6 | 0.216309 | 1.83463 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1341.33 | 0.787267 | 6207.86ms | 83958 | 30 | 6.62547e+06 | 59693.3 | 0.350565 | 1.84448 | 2(Tie) | true |
| simdjson (ondemand) | 1065.47 | 0.22026 | 7779.14ms | 83958 | 640 | 1.75343e+07 | 75148.3 | 0.0770797 | 2.32258 | 4(Loss) | true |
