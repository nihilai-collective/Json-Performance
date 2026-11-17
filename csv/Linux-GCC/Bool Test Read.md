
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2415.65 | 0.09159 | 38.5331ms | 905 | 320 | 34.2668 | 357.284 | 0.243434 | 0.949624 | 1(Win) | true |
| Glaze | 610.713 | 0.024985 | 147.07ms | 905 | 80 | 9.97405 | 1413.22 | 0.0424741 | 3.90848 | 2(Loss) | true |
| Jsonifier (two-stage) | 452.082 | 0.0377466 | 195.429ms | 905 | 80 | 41.5441 | 1909.11 | 0.089621 | 5.40135 | 3(Loss) | true |
| simdjson (ondemand) | 210.78 | 0.0567945 | 416.134ms | 905 | 40 | 216.328 | 4094.68 | 0.168183 | 11.6683 | 4(Loss) | true |
