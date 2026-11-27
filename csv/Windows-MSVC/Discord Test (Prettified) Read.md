
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 12271 | 0.131585 | 673.969ms | 83958 | 40 | 2948.72 | 6525 | 0.0255363 | 0.246371 | 1(Win) | true |
| simdjson (stage-1) | 10681.2 | 0.280228 | 761.444ms | 83958 | 80 | 35302.2 | 7496.25 | 0.351406 | 0.282758 | 2(Loss) | true |
