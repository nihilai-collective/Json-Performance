
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4283.69 | 0.197158 | 8210.32ms | 716365 | 640 | 6.32763e+07 | 159484 | 0.415852 | 0.708965 | 1(Win) | true |
| Glaze | 1732.48 | 0.215103 | 5027.44ms | 716365 | 640 | 4.60475e+08 | 394337 | 0.388853 | 1.7534 | 2(Loss) | true |
