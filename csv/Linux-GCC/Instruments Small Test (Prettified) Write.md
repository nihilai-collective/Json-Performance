
----
### Instruments Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20432.8 | 0.0905029 | 46.0195ms | 9249 | 320 | 48.8436 | 431.684 | 0.149625 | 0.113869 | 1(Win) | true |
| Glaze | 3236.77 | 0.213779 | 267.02ms | 9249 | 30 | 1018.16 | 2725.1 | 0.293201 | 0.757303 | 2(Loss) | true |
| simdjson (reflection) | 547.165 | 0.712432 | 1647.5ms | 9249 | 160 | 2.11038e+06 | 16120.4 | 0.172194 | 4.51723 | 3(Loss) | true |
