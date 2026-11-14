
----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15747.8 | 0.146801 | 804.104ms | 11812 | 160 | 176.435 | 715.325 | 0.0559499 | 0.339719 | 1.63021 | 0.257365 | 8.73053e-05 | 1.58737e-05 | 1.05825e-06 | 1(Win) | true |
| simdjson (reflection) | 9955.48 | 0.0743417 | 843.948ms | 11812 | 2560 | 1811.45 | 1131.52 | 0.0353633 | 0.530317 | 2.37246 | 0.355409 | 0.000107643 | 2.99616e-05 | 1.16738e-05 | 2(Loss) | true |
| Glaze | 4580.49 | 0.140199 | 989.647ms | 11812 | 4890 | 58133.1 | 2459.3 | 0.0908623 | 1.12693 | 4.61895 | 0.71512 | 9.44414e-05 | 3.61145e-05 | 1.53392e-05 | 3(Loss) | true |
