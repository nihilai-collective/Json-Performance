
----
### CitmCatalog Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 697.791 | 0.0427582 | 8791.12ms | 500299 | 640 | 5.4705e+07 | 683761 | 0.0657833 | 7.3146 | 35.8674 | 7.47256 | 0.0224518 | 0.0121637 | 0.000133183 | 1(Win) | true |
| simdjson (ondemand) | 413.377 | 0.105765 | 7351.43ms | 500299 | 320 | 4.76869e+08 | 1.15421e+06 | 0.0946165 | 12.2924 | 65.5822 | 13.0737 | 0.0340566 | 0.0181915 | 0.000242592 | 2(Loss) | true |
