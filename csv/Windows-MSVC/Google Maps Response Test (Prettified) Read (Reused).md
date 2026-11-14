
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2544.86 | 0.103857 | 1040.33ms | 25388 | 4890 | 477428 | 9514.05 | 0.309981 | 1.1915 | 1(Win) | true |
| Jsonifier | 2444.8 | 0.0813697 | 1084.02ms | 25388 | 4890 | 317544 | 9903.42 | 0.0581843 | 1.24048 | 2(Loss) | true |
| Glaze | 1712.83 | 0.1082 | 1508.69ms | 25388 | 640 | 149715 | 14135.6 | 0.172735 | 1.77163 | 3(Loss) | true |
| simdjson (ondemand) | 1332.63 | 0.0954021 | 1927.71ms | 25388 | 2560 | 769122 | 18168.5 | 0.0760525 | 2.27744 | 4(Loss) | true |
