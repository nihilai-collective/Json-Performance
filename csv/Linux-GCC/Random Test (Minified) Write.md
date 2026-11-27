
----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14657.5 | 0.130719 | 3055.76ms | 461466 | 1280 | 1.97174e+06 | 30024.8 | 0.047137 | 0.168733 | 1(Win) | true |
| simdjson (reflection) | 10413.4 | 0.608333 | 4293.96ms | 461466 | 40 | 2.64387e+06 | 42261.8 | 0.307878 | 0.237591 | 2(Loss) | true |
| Glaze | 3183.03 | 0.128833 | 6847.55ms | 461466 | 1280 | 4.06125e+07 | 138261 | 0.00182058 | 0.777613 | 3(Loss) | true |
