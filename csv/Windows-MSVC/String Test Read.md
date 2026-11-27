
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 605.686 | 0.233913 | 687.696ms | 4215 | 30 | 7229.89 | 6636.67 | 0.100351 | 4.06335 | 1(Win) | true |
| Glaze | 477.782 | 0.203357 | 812.47ms | 4215 | 30 | 8781.61 | 8413.33 | 0.238284 | 5.16667 | 2(Loss) | true |
| simdjson (ondemand) | 382.957 | 0.261055 | 1094.29ms | 4215 | 1280 | 961098 | 10496.6 | 0.108549 | 6.43919 | 3(Loss) | true |
