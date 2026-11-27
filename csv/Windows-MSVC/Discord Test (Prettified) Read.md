
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1680.94 | 0.834807 | 5083.22ms | 83958 | 30 | 4.74368e+06 | 47633.3 | 0.0630208 | 1.80759 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1452.62 | 0.910992 | 5926.1ms | 83958 | 40 | 1.00857e+07 | 55120 | 1.0176 | 2.09118 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1446.15 | 0.354664 | 5906.59ms | 83958 | 30 | 1.15678e+06 | 55366.7 | 0.060241 | 2.10025 | 2(Tie) | true |
| simdjson (ondemand) | 996.034 | 1.02349 | 7967.4ms | 83958 | 2560 | 1.73295e+09 | 80387.4 | 1.02214 | 3.04992 | 4(Loss) | true |
