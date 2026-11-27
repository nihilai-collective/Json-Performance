
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2834.55 | 0.279492 | 358.459ms | 9378 | 2560 | 199082 | 3155.2 | 0.228717 | 1(Win) | true |
| Jsonifier (two-stage) | 2463.79 | 0.299021 | 406.782ms | 9378 | 2560 | 301618 | 3630 | 0.0385526 | 2(Loss) | true |
| simdjson (reflection) | 2188.94 | 0.176491 | 453.584ms | 9378 | 2560 | 133119 | 4085.8 | 0.235513 | 3(Loss) | true |
| Glaze | 1850.75 | 0.19052 | 530.647ms | 9378 | 2560 | 216993 | 4832.4 | 0.0455468 | 4(Loss) | true |
| simdjson (ondemand) | 1632.12 | 0.154357 | 595.819ms | 9378 | 4890 | 349844 | 5479.71 | 0.12378 | 5(Loss) | true |
