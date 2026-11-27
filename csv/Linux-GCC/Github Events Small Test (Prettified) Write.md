
----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15298.8 | 0.13284 | 20.2914ms | 2866 | 640 | 36.0475 | 178.656 | 0.0507002 | 0.138198 | 1(Win) | true |
| Glaze | 4432.75 | 0.266046 | 65.9378ms | 2866 | 30 | 80.731 | 616.6 | 0.325415 | 0.534275 | 2(Loss) | true |
| simdjson (reflection) | 610.532 | 0.113254 | 457.03ms | 2866 | 30 | 771.2 | 4476.8 | 0.306962 | 4.03088 | 3(Loss) | true |
