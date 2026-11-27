
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3131.72 | 0.240947 | 288.731ms | 9378 | 40 | 1893.91 | 2855.8 | 0.0175113 | 0.783205 | 1(Win) | true |
| simdjson (reflection) | 2936.91 | 0.0733697 | 310.105ms | 9378 | 160 | 798.716 | 3045.22 | 0.115066 | 0.835775 | 2(Loss) | true |
| Jsonifier (two-stage) | 2866.74 | 0.0974745 | 316.93ms | 9378 | 30 | 277.426 | 3119.77 | 0.140164 | 0.856586 | 3(Loss) | true |
| Glaze | 2498.43 | 0.0546158 | 360.033ms | 9378 | 40 | 152.892 | 3579.68 | 0.148536 | 0.983576 | 4(Loss) | true |
| simdjson (ondemand) | 2439.87 | 0.257546 | 372.767ms | 9378 | 1280 | 114079 | 3665.58 | 0.644717 | 1.00729 | 5(Loss) | true |
