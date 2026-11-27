
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3288.22 | 0.108415 | 305.912ms | 9378 | 40 | 347.804 | 2719.88 | 0.200472 | 0.745636 | 1(Win) | true |
| simdjson (reflection) | 3084.62 | 0.077539 | 310.318ms | 9378 | 30 | 151.628 | 2899.4 | 0.0103459 | 0.79641 | 2(Loss) | true |
| Jsonifier (two-stage) | 3035.35 | 0.104774 | 313.868ms | 9378 | 30 | 285.913 | 2946.47 | 0.159259 | 0.808069 | 3(Loss) | true |
| Glaze | 2671.5 | 0.0782699 | 354.519ms | 9378 | 30 | 205.978 | 3347.77 | 0.0089604 | 0.92005 | 4(Loss) | true |
| simdjson (ondemand) | 2615.28 | 0.0610502 | 353.824ms | 9378 | 160 | 697.393 | 3419.73 | 0.708632 | 0.939227 | 5(Loss) | true |
