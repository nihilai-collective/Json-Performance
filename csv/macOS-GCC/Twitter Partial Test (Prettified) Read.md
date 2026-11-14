
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4873.04 | 0.412258 | 6523.92ms | 631514 | 640 | 1.66144e+08 | 123590 | 0.631522 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4786.76 | 1.20909 | 6597.34ms | 631514 | 160 | 3.70273e+08 | 125818 | 2.65412 | 1(Tie) | true |
| simdjson (reflection) | 4353.76 | 0.0610994 | 7225ms | 631514 | 2560 | 1.82873e+07 | 138331 | 1.25407 | 3(Loss) | true |
| simdjson (ondemand) | 4040.65 | 0.252691 | 7702.52ms | 631514 | 2560 | 3.63147e+08 | 149050 | 1.47809 | 4(Loss) | true |
| Glaze | 2772.44 | 0.28921 | 6251.71ms | 631514 | 320 | 1.26304e+08 | 217230 | 0.617804 | 5(Loss) | true |
