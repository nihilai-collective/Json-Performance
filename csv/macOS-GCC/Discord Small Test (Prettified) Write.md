
----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12396.5 | 1.25661 | 60.3259ms | 7376 | 4890 | 248627 | 567.44 | 1.004 | 1(Win) | true |
| Glaze | 2270.89 | 1.95533 | 347.294ms | 7376 | 30 | 110055 | 3097.6 | 0 | 2(Loss) | true |
| simdjson (reflection) | 270.829 | 0.715027 | 2340.43ms | 7376 | 640 | 2.20737e+07 | 25973.2 | 2.84727 | 3(Loss) | true |
