
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3228.28 | 0.10011 | 293.663ms | 9378 | 40 | 307.676 | 2770.38 | 0.0393895 | 0.75909 | 1(Win) | true |
| Jsonifier | 3139.47 | 0.0667541 | 308.711ms | 9378 | 80 | 289.304 | 2848.75 | 0.0894329 | 0.781191 | 2(Loss) | true |
| simdjson (reflection) | 3043.42 | 0.140441 | 331.462ms | 9378 | 40 | 681.31 | 2938.65 | 0.372871 | 0.806142 | 3(Loss) | true |
| Glaze | 2789.2 | 0.0792466 | 342.949ms | 9378 | 30 | 193.707 | 3206.5 | 0.0841331 | 0.8806 | 4(Loss) | true |
| simdjson (ondemand) | 2488.27 | 0.0592797 | 372.354ms | 9378 | 160 | 726.367 | 3594.28 | 0.277422 | 0.987569 | 5(Loss) | true |
