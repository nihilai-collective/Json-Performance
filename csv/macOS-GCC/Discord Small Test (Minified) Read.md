
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1125.58 | 0.709692 | 423.478ms | 4857 | 160 | 136472 | 4115.2 | 0.077821 | 1(Win) | true |
| simdjson (ondemand) | 618.754 | 0.381802 | 714.429ms | 4857 | 1280 | 1.04565e+06 | 7486 | 0.679297 | 2(Loss) | true |
