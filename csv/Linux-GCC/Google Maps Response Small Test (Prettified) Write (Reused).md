
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 29774.8 | 0.164078 | 39.4533ms | 11521 | 1280 | 469.242 | 369.013 | 0.0378823 | 0.0771059 | 1(Win) | true |
| Glaze | 6178.05 | 0.063577 | 179.671ms | 11521 | 80 | 102.275 | 1778.44 | 0.085119 | 0.39478 | 2(Loss) | true |
| simdjson (reflection) | 591.668 | 0.429743 | 1954.76ms | 11521 | 320 | 2.03795e+06 | 18570 | 0.00107702 | 4.17853 | 3(Loss) | true |
