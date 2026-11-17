
----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5182.84 | 0.121742 | 7856.58ms | 6661897 | 30 | 6.68138e+07 | 1.22583e+06 | 0.0799717 | 0.97671 | 2.94099 | 0.261245 | 7.64747e-05 | 0.0279538 | 0.000140621 | 1(Win) | true |
| Glaze | 3230.27 | 0.319708 | 6155.16ms | 6661897 | 30 | 1.18617e+09 | 1.96679e+06 | 0.327093 | 1.55871 | 4.23031 | 0.469317 | 7.72403e-05 | 0.0630812 | 0.00534841 | 2(Loss) | true |
