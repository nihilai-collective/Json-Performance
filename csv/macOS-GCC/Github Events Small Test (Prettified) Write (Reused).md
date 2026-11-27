
----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 14583.5 | 2.98888 | 21.525ms | 2866 | 4890 | 153445 | 187.419 | 7.67526 | -(Win) | false |
| Glaze | 3403.35 | 0.992503 | 83.5269ms | 2866 | 2560 | 162646 | 803.1 | 0.563486 | 2(Loss) | true |
| simdjson (reflection) | 401.426 | 0.334299 | 717.358ms | 2866 | 320 | 165791 | 6808.8 | 0.0352361 | 3(Loss) | true |
