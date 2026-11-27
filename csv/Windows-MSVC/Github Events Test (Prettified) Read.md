
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 976.015 | 0.918997 | 6371.28ms | 65103 | 4890 | 1.67119e+09 | 63612.8 | 1.16136 | 3.11207 | 1(Win) | true |
| Glaze STATISTICAL TIE | 921.13 | 1.87798 | 6899.67ms | 65103 | 640 | 1.02547e+09 | 67403.1 | 0.00510017 | 3.29733 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 904.787 | 0.878186 | 6797.08ms | 65103 | 4890 | 1.77579e+09 | 68620.7 | 0.607114 | 3.35736 | 2(Tie) | true |
| simdjson (ondemand) | 652.018 | 0.963781 | 9464.32ms | 65103 | 2560 | 2.15616e+09 | 95223 | 0.76388 | 4.65941 | 4(Loss) | true |
