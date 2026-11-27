
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2074.14 | 0.099574 | 4427.14ms | 83958 | 1280 | 1.89125e+06 | 38603.2 | 0.00932652 | 1(Win) | true |
| simdjson (ondemand) | 1434.41 | 0.304155 | 6077.53ms | 83958 | 320 | 9.224e+06 | 55820 | 0.176592 | 2(Loss) | true |
