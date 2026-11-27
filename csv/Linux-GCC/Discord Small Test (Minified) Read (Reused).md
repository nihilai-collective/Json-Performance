
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3191.45 | 0.0485692 | 891.489ms | 4857 | 1280 | 636.052 | 1451.38 | 0.0852288 | 1.66767 | 6.69776 | 1.13136 | 0.00020621 | 5.22764e-05 | 1.57633e-05 | 1(Win) | true |
| Glaze | 2599.85 | 0.0739099 | 921.806ms | 4857 | 4890 | 8479.15 | 1781.64 | 0.00964262 | 2.02839 | 8.52357 | 1.58616 | 0.00143153 | 4.36197e-05 | 1.68837e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2034.14 | 0.164371 | 969.401ms | 4857 | 80 | 1120.77 | 2277.12 | 0.141426 | 2.584 | 10.6164 | 1.58102 | 0.000965102 | 0.000113239 | 4.88985e-05 | 3(Loss) | true |
| simdjson (reflection) | 1839.81 | 0.120624 | 1002.08ms | 4857 | 1280 | 11805 | 2517.65 | 0.206159 | 2.83695 | 11.476 | 1.82376 | 0.000871004 | 5.6941e-05 | 9.65102e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1577.51 | 0.0768798 | 1036.9ms | 4857 | 1280 | 6522.68 | 2936.27 | 0.070265 | 3.32342 | 11.9442 | 2.16286 | 0.00259355 | 4.47164e-05 | 4.66466e-06 | 5(Loss) | true |
