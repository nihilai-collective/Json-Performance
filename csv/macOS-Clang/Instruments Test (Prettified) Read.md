
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2828.18 | 0.0623184 | 6260.25ms | 183677 | 4890 | 7.28511e+06 | 61936.6 | 0.11032 | 1(Win) | true |
| Jsonifier (two-stage) | 2527.68 | 0.0858871 | 7003.76ms | 183677 | 2560 | 9.06901e+06 | 69299.8 | 0.0164163 | 2(Loss) | true |
| Glaze | 1920.6 | 0.0728969 | 9216.43ms | 183677 | 2560 | 1.13161e+07 | 91205.1 | 0.0242588 | 3(Loss) | true |
| simdjson (ondemand) | 1117.19 | 0.0679014 | 8087.79ms | 183677 | 2560 | 2.90172e+07 | 156794 | 0.0219871 | 4(Loss) | true |
