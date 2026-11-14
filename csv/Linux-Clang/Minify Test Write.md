
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3674.16 | 0.0850192 | 6599.41ms | 466906 | 1280 | 1.3589e+07 | 121191 | 0.213795 | 1.36026 | 6.67782 | 0.888273 | 0.00196203 | 0.00065803 | 1.87303e-05 | 1(Win) | true |
| Glaze | 2653.73 | 0.0477663 | 8946.07ms | 466906 | 2560 | 1.64448e+07 | 167793 | 0.0143564 | 1.90125 | 7.7472 | 1.47693 | 0.00239906 | 0.000656647 | 2.34698e-05 | 2(Loss) | true |
| simdjson (ondemand) | 1763.57 | 0.087243 | 6677.84ms | 466906 | 640 | 3.10538e+07 | 252485 | 0.000912173 | 2.8474 | 12.571 | 1.66785 | 0.00397908 | 0.0820926 | 3.33445e-05 | 3(Loss) | true |
