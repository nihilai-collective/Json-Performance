
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13607.8 | 0.0633952 | 1506.5ms | 213963 | 4890 | 441902 | 14995.2 | 0.0416696 | 0.222997 | 1(Win) | true |
| Glaze | 4428.31 | 0.698008 | 4743.93ms | 213963 | 640 | 6.62067e+07 | 46078.8 | 0.0338978 | 0.686009 | 2(Loss) | true |
